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
struct TYPE_7__ {int nr_of_channels; TYPE_1__* audio_streams; } ;
typedef  TYPE_3__ dvd_priv_t ;
struct TYPE_5__ {int id; int language; } ;

/* Variables and functions */

__attribute__((used)) static int dvd_lang_from_aid(stream_t *stream, int id) {
  dvd_priv_t *d;
  int i;
  if (!stream) return 0;
  d = stream->priv;
  if (!d) return 0;
  for(i=0;i<d->nr_of_channels;i++) {
    if(d->audio_streams[i].id==id)
      return d->audio_streams[i].language;
  }
  return 0;
}