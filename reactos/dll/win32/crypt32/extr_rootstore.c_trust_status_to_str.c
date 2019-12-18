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
typedef  int /*<<< orphan*/  buf ;
typedef  int DWORD ;

/* Variables and functions */
 int CERT_TRUST_HAS_EXCLUDED_NAME_CONSTRAINT ; 
 int CERT_TRUST_HAS_NOT_DEFINED_NAME_CONSTRAINT ; 
 int CERT_TRUST_HAS_NOT_PERMITTED_NAME_CONSTRAINT ; 
 int CERT_TRUST_HAS_NOT_SUPPORTED_NAME_CONSTRAINT ; 
 int CERT_TRUST_INVALID_BASIC_CONSTRAINTS ; 
 int CERT_TRUST_INVALID_EXTENSION ; 
 int CERT_TRUST_INVALID_NAME_CONSTRAINTS ; 
 int CERT_TRUST_INVALID_POLICY_CONSTRAINTS ; 
 int CERT_TRUST_IS_CYCLIC ; 
 int CERT_TRUST_IS_NOT_SIGNATURE_VALID ; 
 int CERT_TRUST_IS_NOT_TIME_NESTED ; 
 int CERT_TRUST_IS_NOT_TIME_VALID ; 
 int CERT_TRUST_IS_NOT_VALID_FOR_USAGE ; 
 int CERT_TRUST_IS_OFFLINE_REVOCATION ; 
 int CERT_TRUST_IS_REVOKED ; 
 int CERT_TRUST_IS_UNTRUSTED_ROOT ; 
 int CERT_TRUST_NO_ISSUANCE_CHAIN_POLICY ; 
 int CERT_TRUST_REVOCATION_STATUS_UNKNOWN ; 
 scalar_t__ snprintf (char*,int,char*) ; 

__attribute__((used)) static const char *trust_status_to_str(DWORD status)
{
    static char buf[1024];
    int pos = 0;

    if (status & CERT_TRUST_IS_NOT_TIME_VALID)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\texpired");
    if (status & CERT_TRUST_IS_NOT_TIME_NESTED)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\tbad time nesting");
    if (status & CERT_TRUST_IS_REVOKED)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\trevoked");
    if (status & CERT_TRUST_IS_NOT_SIGNATURE_VALID)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\tbad signature");
    if (status & CERT_TRUST_IS_NOT_VALID_FOR_USAGE)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\tbad usage");
    if (status & CERT_TRUST_IS_UNTRUSTED_ROOT)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\tuntrusted root");
    if (status & CERT_TRUST_REVOCATION_STATUS_UNKNOWN)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tunknown revocation status");
    if (status & CERT_TRUST_IS_CYCLIC)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\tcyclic chain");
    if (status & CERT_TRUST_INVALID_EXTENSION)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tunsupported critical extension");
    if (status & CERT_TRUST_INVALID_POLICY_CONSTRAINTS)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "\n\tbad policy");
    if (status & CERT_TRUST_INVALID_BASIC_CONSTRAINTS)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tbad basic constraints");
    if (status & CERT_TRUST_INVALID_NAME_CONSTRAINTS)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tbad name constraints");
    if (status & CERT_TRUST_HAS_NOT_SUPPORTED_NAME_CONSTRAINT)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tunsupported name constraint");
    if (status & CERT_TRUST_HAS_NOT_DEFINED_NAME_CONSTRAINT)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tundefined name constraint");
    if (status & CERT_TRUST_HAS_NOT_PERMITTED_NAME_CONSTRAINT)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tdisallowed name constraint");
    if (status & CERT_TRUST_HAS_EXCLUDED_NAME_CONSTRAINT)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\texcluded name constraint");
    if (status & CERT_TRUST_IS_OFFLINE_REVOCATION)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\trevocation server offline");
    if (status & CERT_TRUST_NO_ISSUANCE_CHAIN_POLICY)
        pos += snprintf(buf + pos, sizeof(buf) - pos,
         "\n\tno issuance policy");
    return buf;
}