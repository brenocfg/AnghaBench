#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int sct_source_t ;
struct TYPE_4__ {int source; int /*<<< orphan*/  validation_status; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LOG_ENTRY_TYPE_PRECERT ; 
 int /*<<< orphan*/  CT_LOG_ENTRY_TYPE_X509 ; 
#define  SCT_SOURCE_OCSP_STAPLED_RESPONSE 131 
#define  SCT_SOURCE_TLS_EXTENSION 130 
#define  SCT_SOURCE_UNKNOWN 129 
#define  SCT_SOURCE_X509V3_EXTENSION 128 
 int /*<<< orphan*/  SCT_VALIDATION_STATUS_NOT_SET ; 
 int SCT_set_log_entry_type (TYPE_1__*,int /*<<< orphan*/ ) ; 

int SCT_set_source(SCT *sct, sct_source_t source)
{
    sct->source = source;
    sct->validation_status = SCT_VALIDATION_STATUS_NOT_SET;
    switch (source) {
    case SCT_SOURCE_TLS_EXTENSION:
    case SCT_SOURCE_OCSP_STAPLED_RESPONSE:
        return SCT_set_log_entry_type(sct, CT_LOG_ENTRY_TYPE_X509);
    case SCT_SOURCE_X509V3_EXTENSION:
        return SCT_set_log_entry_type(sct, CT_LOG_ENTRY_TYPE_PRECERT);
    case SCT_SOURCE_UNKNOWN:
        break;
    }
    /* if we aren't sure, leave the log entry type alone */
    return 1;
}