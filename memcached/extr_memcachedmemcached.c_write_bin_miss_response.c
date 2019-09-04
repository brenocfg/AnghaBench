#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  protocol_binary_response_header ;
struct TYPE_7__ {char* wbuf; int /*<<< orphan*/  write_and_go; } ;
typedef  TYPE_1__ conn ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_KEY_ENOENT ; 
 int /*<<< orphan*/  add_bin_header (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  add_iov (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  conn_mwrite ; 
 int /*<<< orphan*/  conn_new_cmd ; 
 int /*<<< orphan*/  conn_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  write_bin_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_bin_miss_response(conn *c, char *key, size_t nkey) {
    if (nkey) {
        char *ofs = c->wbuf + sizeof(protocol_binary_response_header);
        add_bin_header(c, PROTOCOL_BINARY_RESPONSE_KEY_ENOENT,
                0, nkey, nkey);
        memcpy(ofs, key, nkey);
        add_iov(c, ofs, nkey);
        conn_set_state(c, conn_mwrite);
        c->write_and_go = conn_new_cmd;
    } else {
        write_bin_error(c, PROTOCOL_BINARY_RESPONSE_KEY_ENOENT,
                        NULL, 0);
    }
}