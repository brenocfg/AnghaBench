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
struct TYPE_3__ {scalar_t__ pbPreparedSrc; scalar_t__ pbSrc; scalar_t__ cbPreparedSrcLength; scalar_t__ cbSrcLength; scalar_t__ pbPreparedDst; scalar_t__ pbDst; scalar_t__ cbPreparedDstLength; scalar_t__ cbDstLength; } ;
typedef  TYPE_1__* PACMDRVSTREAMHEADER ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static BOOL ACM_ValidatePointers(PACMDRVSTREAMHEADER padsh)
{
    /* check that pointers have not been modified */
    return !(padsh->pbPreparedSrc != padsh->pbSrc ||
             padsh->cbPreparedSrcLength < padsh->cbSrcLength ||
             padsh->pbPreparedDst != padsh->pbDst ||
             padsh->cbPreparedDstLength < padsh->cbDstLength);
}