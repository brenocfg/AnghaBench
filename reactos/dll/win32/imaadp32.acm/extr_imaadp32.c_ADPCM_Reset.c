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
struct TYPE_3__ {scalar_t__ stepIndexR; scalar_t__ stepIndexL; } ;
typedef  int /*<<< orphan*/  PACMDRVSTREAMINSTANCE ;
typedef  TYPE_1__ AcmAdpcmData ;

/* Variables and functions */

__attribute__((used)) static	void	ADPCM_Reset(PACMDRVSTREAMINSTANCE adsi, AcmAdpcmData* aad)
{
    aad->stepIndexL = aad->stepIndexR = 0;
}