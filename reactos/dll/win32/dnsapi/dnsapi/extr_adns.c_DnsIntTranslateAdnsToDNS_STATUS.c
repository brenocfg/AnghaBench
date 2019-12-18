#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DNS_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
#define  adns_s_nomemory 130 
#define  adns_s_ok 129 
#define  adns_s_systemfail 128 

DNS_STATUS
DnsIntTranslateAdnsToDNS_STATUS(int Status)
{
    switch(Status)
    {
        case adns_s_ok:
            return ERROR_SUCCESS;

        case adns_s_nomemory:
        case adns_s_systemfail:
        default: /* There really aren't any general errors in the dns part. */
            return ERROR_OUTOFMEMORY;
    }
}