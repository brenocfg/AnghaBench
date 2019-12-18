#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ buf; } ;
struct TYPE_5__ {TYPE_3__ ntlmssp; } ;
struct SMBSTUFF {TYPE_2__ spnego; } ;
struct TYPE_4__ {struct SMBSTUFF smb; } ;
struct ProtocolState {TYPE_1__ sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntlmssp_cleanup (TYPE_3__*) ; 

__attribute__((used)) static void
smb_cleanup(struct ProtocolState *pstate)
{
    struct SMBSTUFF *smb = &pstate->sub.smb;
    if (smb->spnego.ntlmssp.buf)
        ntlmssp_cleanup(&smb->spnego.ntlmssp);
}