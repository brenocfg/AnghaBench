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
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {int cur_cell; int last_cell; int dvd_angle; TYPE_2__* cur_pgc; } ;
typedef  TYPE_3__ dvd_priv_t ;
struct TYPE_6__ {TYPE_1__* cell_playback; } ;
struct TYPE_5__ {scalar_t__ block_type; scalar_t__ block_mode; } ;

/* Variables and functions */
 scalar_t__ BLOCK_MODE_LAST_CELL ; 
 scalar_t__ BLOCK_TYPE_ANGLE_BLOCK ; 
 int /*<<< orphan*/  MP_DBG (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int dvd_next_cell(stream_t *stream, dvd_priv_t *d) {
  int next_cell=d->cur_cell;

  MP_DBG(stream, "dvd_next_cell: next1=0x%X  \n",next_cell);
  if( d->cur_pgc->cell_playback[ next_cell ].block_type == BLOCK_TYPE_ANGLE_BLOCK ) {
    while(next_cell<d->last_cell) {
      if( d->cur_pgc->cell_playback[next_cell].block_mode == BLOCK_MODE_LAST_CELL )
        break;
      ++next_cell;
    }
  }
  MP_DBG(stream, "dvd_next_cell: next2=0x%X  \n",next_cell);

  ++next_cell;
  if(next_cell>=d->last_cell)
    return -1; // EOF
  if(d->cur_pgc->cell_playback[next_cell].block_type == BLOCK_TYPE_ANGLE_BLOCK ) {
    next_cell+=d->dvd_angle-1;
    if(next_cell>=d->last_cell)
      return -1; // EOF
  }
  MP_DBG(stream, "dvd_next_cell: next3=0x%X  \n",next_cell);
  return next_cell;
}