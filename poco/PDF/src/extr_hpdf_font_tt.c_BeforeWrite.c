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
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_Dict ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDescriptor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_STATUS
BeforeWrite  (HPDF_Dict   obj)
{
    HPDF_PTRACE ((" HPDF_TTFont_BeforeWrite\n"));

    return CreateDescriptor (obj);
}