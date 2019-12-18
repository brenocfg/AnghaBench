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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  cbData; void* pbData; } ;
struct TYPE_5__ {TYPE_1__ Value; int /*<<< orphan*/  fCritical; scalar_t__ pszObjId; } ;
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CERT_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ X509_ENHANCED_KEY_USAGE ; 
 int /*<<< orphan*/ * crypt_format_extension (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *format_enhanced_key_usage_value(void *pb, DWORD cb)
{
    CERT_EXTENSION ext;

    ext.pszObjId = (LPSTR)X509_ENHANCED_KEY_USAGE;
    ext.fCritical = FALSE;
    ext.Value.pbData = pb;
    ext.Value.cbData = cb;
    return crypt_format_extension(&ext, 0);
}