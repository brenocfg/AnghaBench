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
typedef  int /*<<< orphan*/  SCT ;

/* Variables and functions */
#define  SCT_VALIDATION_STATUS_INVALID 133 
#define  SCT_VALIDATION_STATUS_NOT_SET 132 
#define  SCT_VALIDATION_STATUS_UNKNOWN_LOG 131 
#define  SCT_VALIDATION_STATUS_UNKNOWN_VERSION 130 
#define  SCT_VALIDATION_STATUS_UNVERIFIED 129 
#define  SCT_VALIDATION_STATUS_VALID 128 
 int SCT_get_validation_status (int /*<<< orphan*/  const*) ; 

const char *SCT_validation_status_string(const SCT *sct)
{

    switch (SCT_get_validation_status(sct)) {
    case SCT_VALIDATION_STATUS_NOT_SET:
        return "not set";
    case SCT_VALIDATION_STATUS_UNKNOWN_VERSION:
        return "unknown version";
    case SCT_VALIDATION_STATUS_UNKNOWN_LOG:
        return "unknown log";
    case SCT_VALIDATION_STATUS_UNVERIFIED:
        return "unverified";
    case SCT_VALIDATION_STATUS_INVALID:
        return "invalid";
    case SCT_VALIDATION_STATUS_VALID:
        return "valid";
    }
    return "unknown status";
}