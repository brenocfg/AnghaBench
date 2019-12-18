#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Banner1 {void* http_fields; void* memcached_stats; void* memcached_responses; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_anchored; int /*<<< orphan*/  id; scalar_t__ pattern; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_anchored; int /*<<< orphan*/  id; scalar_t__ pattern; } ;

/* Variables and functions */
 char* MALLOC (size_t) ; 
 int /*<<< orphan*/  SMACK_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* memcached_responses ; 
 TYPE_1__* memcached_stats ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 
 void* sm_memcached_responses ; 
 void* sm_memcached_stats ; 
 int /*<<< orphan*/  smack_add_pattern (void*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smack_compile (void*) ; 
 void* smack_create (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (scalar_t__) ; 

__attribute__((used)) static void *
memcached_init(struct Banner1 *b)
{
    unsigned i;

    /*
     * These match response codes
     */
    b->memcached_responses = smack_create("memcached-responses", SMACK_CASE_INSENSITIVE);
    for (i=0; memcached_responses[i].pattern; i++) {
        char *tmp;
        unsigned j;
        size_t len;

        len = strlen(memcached_responses[i].pattern);
        tmp = MALLOC(len + 2);
        memcpy(tmp, memcached_responses[i].pattern, len);
        tmp[len+1] = '\0';

        /* Add all patterns 4 times, once each for the possible whitespace */
        for (j=0; j<4; j++) {
            tmp[len] = " \t\r\n"[j];
            smack_add_pattern(
                          b->memcached_responses,
                          tmp,
                          (unsigned)len+1,
                          memcached_responses[i].id,
                          memcached_responses[i].is_anchored);
        }

        free(tmp);
    }
    smack_compile(b->memcached_responses);
    sm_memcached_responses = b->memcached_responses;

    /*
     * These match stats we might be interested in
     */
    b->memcached_stats = smack_create("memcached-stats", SMACK_CASE_INSENSITIVE);
    for (i=0; memcached_stats[i].pattern; i++) {
        char *tmp;
        unsigned j;
        size_t len;

        len = strlen(memcached_stats[i].pattern);
        tmp = MALLOC(len + 2);
        memcpy(tmp, memcached_stats[i].pattern, len);
        tmp[len+1] = '\0';

        /* Add all patterns 4 times, once each for the possible whitespace */
        for (j=0; j<4; j++) {
            tmp[len] = " \t\r\n"[j];
            smack_add_pattern(
                          b->memcached_stats,
                          tmp,
                          (unsigned)len+1,
                          memcached_stats[i].id,
                          memcached_stats[i].is_anchored);
        }

        free(tmp);
    }
    smack_compile(b->memcached_stats);
    sm_memcached_stats = b->memcached_stats;

    return b->http_fields;
}