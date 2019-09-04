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
typedef  int /*<<< orphan*/  PyMODINIT_FUNC ;

/* Variables and functions */
 int /*<<< orphan*/  LoadfontMethods ; 
 int /*<<< orphan*/  Py_InitModule (char*,int /*<<< orphan*/ ) ; 

PyMODINIT_FUNC initloadfont(void) {
  Py_InitModule("loadfont", LoadfontMethods);
}