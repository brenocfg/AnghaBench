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
typedef  int /*<<< orphan*/  HPDF_EmbeddedFile ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_TRUE ; 
 int /*<<< orphan*/  HPDF_UNUSED (int /*<<< orphan*/ ) ; 

HPDF_BOOL
HPDF_EmbeddedFile_Validate  (HPDF_EmbeddedFile  emfile)
{
    HPDF_UNUSED (emfile);
    return HPDF_TRUE;
}