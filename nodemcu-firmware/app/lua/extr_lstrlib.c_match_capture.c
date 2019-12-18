#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* src_end; TYPE_1__* capture; } ;
struct TYPE_5__ {size_t len; int /*<<< orphan*/  init; } ;
typedef  TYPE_2__ MatchState ;

/* Variables and functions */
 int check_capture (TYPE_2__*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static const char *match_capture (MatchState *ms, const char *s, int l) {
  size_t len;
  l = check_capture(ms, l);
  len = ms->capture[l].len;
  if ((size_t)(ms->src_end-s) >= len &&
      memcmp(ms->capture[l].init, s, len) == 0)
    return s+len;
  else return NULL;
}