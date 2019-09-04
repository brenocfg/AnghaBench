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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int nid; scalar_t__ amask; } ;
typedef  TYPE_1__ SSL_CERT_LOOKUP ;

/* Variables and functions */
 scalar_t__ OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*,size_t) ; 
 int /*<<< orphan*/  TEST_note (char*,scalar_t__,scalar_t__) ; 
 TYPE_1__* ssl_cert_info ; 

__attribute__((used)) static int do_test_cert_table(int nid, uint32_t amask, size_t idx,
                              const char *idxname)
{
    const SSL_CERT_LOOKUP *clu = &ssl_cert_info[idx];

    if (clu->nid == nid && clu->amask == amask)
        return 1;

    TEST_error("Invalid table entry for certificate type %s, index %zu",
               idxname, idx);
    if (clu->nid != nid)
        TEST_note("Expected %s, got %s\n", OBJ_nid2sn(nid),
                  OBJ_nid2sn(clu->nid));
    if (clu->amask != amask)
        TEST_note("Expected auth mask 0x%x, got 0x%x\n", amask, clu->amask);
    return 0;
}