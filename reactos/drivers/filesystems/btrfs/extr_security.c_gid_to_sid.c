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
typedef  int uint32_t ;
struct TYPE_5__ {int revision; int elements; int* auth; int* nums; } ;
typedef  TYPE_1__ sid_header ;
typedef  int UCHAR ;
typedef  TYPE_1__* PSID ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 

__attribute__((used)) static void gid_to_sid(uint32_t gid, PSID* sid) {
    sid_header* sh;
    UCHAR els;

    // FIXME - do this properly?

    // fallback to S-1-22-2-X, Samba's SID scheme
    els = 2;
    sh = ExAllocatePoolWithTag(PagedPool, sizeof(sid_header) + ((els - 1) * sizeof(uint32_t)), ALLOC_TAG);
    if (!sh) {
        ERR("out of memory\n");
        *sid = NULL;
        return;
    }

    sh->revision = 1;
    sh->elements = els;

    sh->auth[0] = 0;
    sh->auth[1] = 0;
    sh->auth[2] = 0;
    sh->auth[3] = 0;
    sh->auth[4] = 0;
    sh->auth[5] = 22;

    sh->nums[0] = 2;
    sh->nums[1] = gid;

    *sid = sh;
}