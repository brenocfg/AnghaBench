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
struct TYPE_4__ {void (* free ) (struct SCV_NB10_HEADER*) ;} ;
typedef  TYPE_1__ SCV_NB10_HEADER ;

/* Variables and functions */
 scalar_t__ free_cv_nb10_header ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_cv_nb10_header(SCV_NB10_HEADER* cv_nb10_header) {
	memset (cv_nb10_header, 0, sizeof (SCV_NB10_HEADER));
	cv_nb10_header->free = (void (*)(struct SCV_NB10_HEADER*))free_cv_nb10_header;
}