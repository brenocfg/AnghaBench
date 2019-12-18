#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  messageTime; } ;
struct TYPE_4__ {TYPE_2__* hdr; } ;
typedef  TYPE_1__ CMP_HDR_TEST_FIXTURE ;

/* Variables and functions */
 int ASN1_TIME_to_tm (int /*<<< orphan*/ ,struct tm*) ; 
 int TEST_true (int) ; 
 struct tm* gmtime (scalar_t__*) ; 
 scalar_t__ mktime (struct tm*) ; 
 int ossl_cmp_hdr_update_messageTime (TYPE_2__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int execute_HDR_update_messageTime_test(CMP_HDR_TEST_FIXTURE *fixture)
{
    struct tm hdrtm;
    time_t hdrtime, before, after, now;

    now = time(NULL);
    before = mktime(gmtime(&now));
    if (!TEST_true(ossl_cmp_hdr_update_messageTime(fixture->hdr)))
        return 0;
    if (!TEST_true(ASN1_TIME_to_tm(fixture->hdr->messageTime, &hdrtm)))
        return 0;

    hdrtime = mktime(&hdrtm);
    if (!TEST_true(before <= hdrtime))
        return 0;
    now = time(NULL);
    after = mktime(gmtime(&now));
    return TEST_true(hdrtime <= after);
}