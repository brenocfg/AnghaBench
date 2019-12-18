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
struct TYPE_3__ {int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Dict ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_MemStream_FreeData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_STATUS
PngAfterWrite  (HPDF_Dict obj)
{
   HPDF_PTRACE ((" PngAfterWrite\n"));

   HPDF_MemStream_FreeData(obj->stream);

   return HPDF_OK;
}