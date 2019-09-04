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
struct MEMCACHEDSTUFF {int /*<<< orphan*/  match; } ;
struct TYPE_3__ {struct MEMCACHEDSTUFF memcached; } ;
struct ProtocolState {unsigned int state; TYPE_1__ sub; } ;
typedef  void const InteractiveData ;
struct BannerOutput {int dummy; } ;
typedef  void Banner1 ;
struct TYPE_4__ {int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
#define  MC_END 133 
#define  MC_STAT 132 
#define  MS_TIME 131 
#define  MS_UPTIME 130 
#define  MS_VERSION 129 
 int /*<<< orphan*/  PROTO_MEMCACHED ; 
#define  SMACK_NOT_FOUND 128 
 int /*<<< orphan*/  UNUSEDPARM (void const*) ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  isspace (unsigned char const) ; 
 TYPE_2__* memcached_stats ; 
 scalar_t__ sm_memcached_responses ; 
 scalar_t__ sm_memcached_stats ; 
 size_t smack_search_next (scalar_t__,int /*<<< orphan*/ *,unsigned char const*,unsigned int*,unsigned int) ; 

__attribute__((used)) static void
memcached_tcp_parse(  
          const struct Banner1 *banner1,
          void *banner1_private,
          struct ProtocolState *pstate,
          const unsigned char *px, size_t length,
          struct BannerOutput *banout,
          struct InteractiveData *more)
{
    unsigned state = pstate->state;
    unsigned i;
    struct MEMCACHEDSTUFF *memcached = &pstate->sub.memcached;
    size_t id;

    UNUSEDPARM(banner1_private);
    UNUSEDPARM(banner1);
    UNUSEDPARM(more);

    if (sm_memcached_responses == 0)
        return;

    for (i=0; i<length; i++) {
        switch (state) {
            case 0: /* command */
                memcached->match = 0;
                /* drop through */
            case 1:
                id = smack_search_next(
                        sm_memcached_responses,
                        &memcached->match,
                        px, &i, (unsigned)length);
                i--;
                switch (id) {
                case SMACK_NOT_FOUND:
                    /* continue processing */
                    break;
                case MC_STAT:
                    if (px[i] == '\n')
                        state = 2; /* premature end of line */
                    else
                        state = 100;
                    break;
                case MC_END:
                    state = 3;
                    break;
                default:
                    state = 2;
                }
                break;

            /* We've reached the end of input */
            case 3:
                i = (unsigned)length;
                break;

            /* Ignore until end of line */
            case 2:
                while (i < length && px[i] != '\n')
                    i++;
                if (px[i] == '\n')
                    state = 0;
                break;
            
            /* process stat */
            case 100:
            case 200:
                if (px[i] == '\n')
                    state = 0;
                else if (isspace(px[i]))
                    continue; /* stay in this space until end of whitespace */
                else {
                    state++;
                    memcached->match = 0;
                    i--;
                }
                break;
            case 101:
                id = smack_search_next(
                        sm_memcached_stats,
                        &memcached->match,
                        px, &i, (unsigned)length);
                i--;
                switch (id) {
                case SMACK_NOT_FOUND:
                    /* continue processing */
                    break;
                case MS_UPTIME:
                case MS_TIME:
                case MS_VERSION:
                    banout_append(banout, PROTO_MEMCACHED, memcached_stats[id].pattern, AUTO_LEN);
                    if (px[i] == '\n')
                        state = 0;
                    else
                        state = 200;
                    banout_append_char(banout, PROTO_MEMCACHED, '=');
                    break;
                default:
                    if (px[i] == '\n')
                        state = 0;
                    else
                        state = 2;
                }
                break;

            case 201:
                if (px[i] == '\r')
                    continue;
                else if (px[i] == '\n') {
                    banout_append_char(banout, PROTO_MEMCACHED, ' ');
                    state = 0;
                    break;
                } else
                    banout_append_char(banout, PROTO_MEMCACHED, px[i]);
                break;
        }
    }
    pstate->state = state;
}