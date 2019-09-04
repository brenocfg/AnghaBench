#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pkt_scr {int /*<<< orphan*/  n; TYPE_4__* pkt; TYPE_3__* scratch; } ;
struct TYPE_8__ {size_t numopts; TYPE_2__* opts; } ;
struct TYPE_7__ {size_t len; int p; } ;
struct TYPE_5__ {int p; int len; } ;
struct TYPE_6__ {TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  assert (struct pkt_scr*) ; 
 int check_segment (unsigned char*,size_t) ; 
 int /*<<< orphan*/  decode_segment (unsigned char*,size_t,int) ; 
 scalar_t__ memcmp (unsigned char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,int) ; 

void write_option(unsigned char *s, size_t len, void *data) {
  struct pkt_scr *state = (struct pkt_scr *)data;
  int res;
  assert(state);

  /* skip empty segments and those that consist of only one or two dots */
  if (memcmp(s, "..", min(len,2)) == 0)
    return;

  res = check_segment(s, len);
  if (res < 0){
    NODE_DBG("not a valid segment\n");
    return;
  }

  if (state->scratch->len < (size_t)res) {
    NODE_DBG("buffer too small for option\n");
    return;
  }

  decode_segment(s, len, state->scratch->p);

  if (res > 0) {
    state->pkt->opts[state->pkt->numopts].buf.p = state->scratch->p;
    state->pkt->opts[state->pkt->numopts].buf.len = res;
    state->scratch->p += res;
    state->scratch->len -= res;
    state->pkt->numopts++;
    state->n++;
  }
}