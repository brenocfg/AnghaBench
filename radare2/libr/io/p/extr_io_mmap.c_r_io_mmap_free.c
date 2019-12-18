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
struct TYPE_5__ {int /*<<< orphan*/  buf; struct TYPE_5__* filename; } ;
typedef  TYPE_1__ RIOMMapFileObj ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_io_mmap_free(RIOMMapFileObj *mmo) {
	free (mmo->filename);
	r_buf_free (mmo->buf);
	memset (mmo, 0, sizeof (RIOMMapFileObj));
	free (mmo);
}