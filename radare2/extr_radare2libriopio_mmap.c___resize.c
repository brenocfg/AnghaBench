#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  RIOMMapFileObj ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int r_io_mmap_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __resize(RIO *io, RIODesc *fd, ut64 size) {
	if (!fd || !fd->data) {
		return -1;
	}
	return r_io_mmap_truncate ((RIOMMapFileObj*)fd->data, size);
}