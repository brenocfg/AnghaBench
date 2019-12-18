#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* user_data; } ;
typedef  int /*<<< orphan*/  HPDF_Error_Rec ;
typedef  TYPE_1__* HPDF_Error ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
HPDF_Error_Init  (HPDF_Error    error,
                  void         *user_data)
{
    HPDF_MemSet(error, 0, sizeof(HPDF_Error_Rec));

    error->user_data = user_data;
}