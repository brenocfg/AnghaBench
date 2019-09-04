#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int NDISKS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * data ; 
 int /*<<< orphan*/ * dataptrs ; 
 int disk_type (int) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int,char*) ; 
 TYPE_1__ raid6_call ; 
 int /*<<< orphan*/  raid6_dual_recov (int,int /*<<< orphan*/ ,int,int,void**) ; 
 int /*<<< orphan*/  recovi ; 
 int /*<<< orphan*/  recovj ; 

__attribute__((used)) static int test_disks(int i, int j)
{
	int erra, errb;

	memset(recovi, 0xf0, PAGE_SIZE);
	memset(recovj, 0xba, PAGE_SIZE);

	dataptrs[i] = recovi;
	dataptrs[j] = recovj;

	raid6_dual_recov(NDISKS, PAGE_SIZE, i, j, (void **)&dataptrs);

	erra = memcmp(data[i], recovi, PAGE_SIZE);
	errb = memcmp(data[j], recovj, PAGE_SIZE);

	if (i < NDISKS-2 && j == NDISKS-1) {
		/* We don't implement the DQ failure scenario, since it's
		   equivalent to a RAID-5 failure (XOR, then recompute Q) */
		erra = errb = 0;
	} else {
		printf("algo=%-8s  faila=%3d(%c)  failb=%3d(%c)  %s\n",
		       raid6_call.name,
		       i, disk_type(i),
		       j, disk_type(j),
		       (!erra && !errb) ? "OK" :
		       !erra ? "ERRB" :
		       !errb ? "ERRA" : "ERRAB");
	}

	dataptrs[i] = data[i];
	dataptrs[j] = data[j];

	return erra || errb;
}