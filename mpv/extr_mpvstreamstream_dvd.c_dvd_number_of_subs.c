#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* priv; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_7__ {int nr_of_subtitles; TYPE_1__* subtitles; } ;
typedef  TYPE_3__ dvd_priv_t ;
struct TYPE_5__ {int id; } ;

/* Variables and functions */

__attribute__((used)) static int dvd_number_of_subs(stream_t *stream) {
  int i;
  int maxid = -1;
  dvd_priv_t *d;
  if (!stream) return -1;
  d = stream->priv;
  if (!d) return -1;
  for (i = 0; i < d->nr_of_subtitles; i++)
    if (d->subtitles[i].id > maxid) maxid = d->subtitles[i].id;
  return maxid + 1;
}