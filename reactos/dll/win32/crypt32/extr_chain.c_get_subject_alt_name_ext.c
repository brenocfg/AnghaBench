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
struct TYPE_3__ {int /*<<< orphan*/  rgExtension; int /*<<< orphan*/  cExtension; } ;
typedef  scalar_t__ PCERT_EXTENSION ;
typedef  TYPE_1__ CERT_INFO ;

/* Variables and functions */
 scalar_t__ CertFindExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOID_SUBJECT_ALT_NAME ; 
 int /*<<< orphan*/  szOID_SUBJECT_ALT_NAME2 ; 

__attribute__((used)) static inline PCERT_EXTENSION get_subject_alt_name_ext(const CERT_INFO *cert)
{
    PCERT_EXTENSION ext;

    ext = CertFindExtension(szOID_SUBJECT_ALT_NAME2,
     cert->cExtension, cert->rgExtension);
    if (!ext)
        ext = CertFindExtension(szOID_SUBJECT_ALT_NAME,
         cert->cExtension, cert->rgExtension);
    return ext;
}