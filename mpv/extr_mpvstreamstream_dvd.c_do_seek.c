#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvd_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stream_drop_buffers (TYPE_1__*) ; 

__attribute__((used)) static int do_seek(stream_t *s, int64_t newpos) {
  stream_drop_buffers(s);
  dvd_seek(s, s->priv,newpos/2048);
  return 1;
}