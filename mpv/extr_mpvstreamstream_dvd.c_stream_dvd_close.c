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
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  dvd_device_current; scalar_t__ dvd_speed; int /*<<< orphan*/  dvd; int /*<<< orphan*/  title; int /*<<< orphan*/  vmg_file; int /*<<< orphan*/  vts_file; } ;
typedef  TYPE_2__ dvd_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVDClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVDCloseFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvd_set_speed (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifoClose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stream_dvd_close(stream_t *s) {
  dvd_priv_t *d = s->priv;
  ifoClose(d->vts_file);
  ifoClose(d->vmg_file);
  DVDCloseFile(d->title);
  DVDClose(d->dvd);
  if (d->dvd_speed)
    dvd_set_speed(s,d->dvd_device_current, -1); /* -1 => restore default */
}