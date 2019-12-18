#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ token_t ;
struct TYPE_12__ {int sasl_started; int rbytes; char* rcurr; int rlbytes; int authenticated; TYPE_2__* thread; int /*<<< orphan*/  try_read_command; } ;
typedef  TYPE_4__ conn ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  auth_errors; int /*<<< orphan*/  auth_cmds; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int MAX_TOKENS ; 
 int authfile_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_closing ; 
 int /*<<< orphan*/  conn_set_state (TYPE_4__*,int /*<<< orphan*/ ) ; 
 char* memchr (char*,char,int) ; 
 int /*<<< orphan*/  out_string (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_strtoul (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 size_t tokenize_command (char*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  try_read_command_ascii ; 

__attribute__((used)) static int try_read_command_asciiauth(conn *c) {
    token_t tokens[MAX_TOKENS];
    size_t ntokens;
    char *cont = NULL;

    // TODO: move to another function.
    if (!c->sasl_started) {
        char *el;
        uint32_t size = 0;

        // impossible for the auth command to be this short.
        if (c->rbytes < 2)
            return 0;

        el = memchr(c->rcurr, '\n', c->rbytes);

        // If no newline after 1k, getting junk data, close out.
        if (!el) {
            if (c->rbytes > 1024) {
                conn_set_state(c, conn_closing);
                return 1;
            }
            return 0;
        }

        // Looking for: "set foo 0 0 N\r\nuser pass\r\n"
        // key, flags, and ttl are ignored. N is used to see if we have the rest.

        // so tokenize doesn't walk past into the value.
        // it's fine to leave the \r in, as strtoul will stop at it.
        *el = '\0';

        ntokens = tokenize_command(c->rcurr, tokens, MAX_TOKENS);
        // ensure the buffer is consumed.
        c->rbytes -= (el - c->rcurr) + 1;
        c->rcurr += (el - c->rcurr) + 1;

        // final token is a NULL ender, so we have one more than expected.
        if (ntokens < 6
                || strcmp(tokens[0].value, "set") != 0
                || !safe_strtoul(tokens[4].value, &size)) {
            out_string(c, "CLIENT_ERROR unauthenticated");
            return 1;
        }

        // we don't actually care about the key at all; it can be anything.
        // we do care about the size of the remaining read.
        c->rlbytes = size + 2;

        c->sasl_started = true; // reuse from binprot sasl, but not sasl :)
    }

    if (c->rbytes < c->rlbytes) {
        // need more bytes.
        return 0;
    }

    cont = c->rcurr;
    // advance buffer. no matter what we're stopping.
    c->rbytes -= c->rlbytes;
    c->rcurr += c->rlbytes;
    c->sasl_started = false;

    // must end with \r\n
    // NB: I thought ASCII sets also worked with just \n, but according to
    // complete_nread_ascii only \r\n is valid.
    if (strncmp(cont + c->rlbytes - 2, "\r\n", 2) != 0) {
        out_string(c, "CLIENT_ERROR bad command line termination");
        return 1;
    }

    // payload should be "user pass", so we can use the tokenizer.
    cont[c->rlbytes - 2] = '\0';
    ntokens = tokenize_command(cont, tokens, MAX_TOKENS);

    if (ntokens < 3) {
        out_string(c, "CLIENT_ERROR bad authentication token format");
        return 1;
    }

    if (authfile_check(tokens[0].value, tokens[1].value) == 1) {
        out_string(c, "STORED");
        c->authenticated = true;
        c->try_read_command = try_read_command_ascii;
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.auth_cmds++;
        pthread_mutex_unlock(&c->thread->stats.mutex);
    } else {
        out_string(c, "CLIENT_ERROR authentication failure");
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.auth_cmds++;
        c->thread->stats.auth_errors++;
        pthread_mutex_unlock(&c->thread->stats.mutex);
    }

    return 1;
}