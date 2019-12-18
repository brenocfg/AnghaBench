#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ success; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* ifree ) (TYPE_2__*) ;TYPE_2__* (* d2i ) (int /*<<< orphan*/ *,unsigned char**,long) ;} ;
typedef  TYPE_1__ TEST_PACKAGE ;
typedef  TYPE_2__ EXPECTED ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ memcmp (TYPE_2__*,TYPE_2__ const*,size_t) ; 
 TYPE_2__* stub1 (int /*<<< orphan*/ *,unsigned char**,long) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static int do_decode(unsigned char *bytes, long nbytes,
                     const EXPECTED *expected, size_t expected_size,
                     const TEST_PACKAGE *package)
{
    EXPECTED *enctst = NULL;
    const unsigned char *start;
    int ret = 0;

    start = bytes;
    enctst = package->d2i(NULL, &bytes, nbytes);
    if (enctst == NULL) {
        if (expected->success == 0) {
            ret = 1;
            ERR_clear_error();
        } else {
            ret = -1;
        }
    } else {
        if (start + nbytes == bytes
            && memcmp(enctst, expected, expected_size) == 0)
            ret = 1;
        else
            ret = 0;
    }

    package->ifree(enctst);
    return ret;
}