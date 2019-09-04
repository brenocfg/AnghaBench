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

/* Variables and functions */
#define  RPCSEC_SSPI_SVC_INTEGRITY 130 
#define  RPCSEC_SSPI_SVC_NONE 129 
#define  RPCSEC_SSPI_SVC_PRIVACY 128 

const char* gssauth_string(int type) {
    switch(type) {
    case RPCSEC_SSPI_SVC_NONE: return "RPCSEC_SSPI_SVC_NONE";
    case RPCSEC_SSPI_SVC_INTEGRITY: return "RPCSEC_SSPI_SVC_INTEGRITY";
    case RPCSEC_SSPI_SVC_PRIVACY: return "RPCSEC_SSPI_SVC_PRIVACY";
    default: return "invalid gss auth type";
    }
}