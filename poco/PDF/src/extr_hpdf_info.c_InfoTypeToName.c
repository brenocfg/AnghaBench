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
typedef  size_t HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_InfoType ;

/* Variables and functions */
 char const** HPDF_INFO_ATTR_NAMES ; 

__attribute__((used)) static const char*
InfoTypeToName  (HPDF_InfoType  type)
{
    HPDF_UINT idx = (HPDF_UINT)type;

    return HPDF_INFO_ATTR_NAMES[idx];
}