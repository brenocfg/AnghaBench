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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  DictionaryObject ;

/* Variables and functions */
 int /*<<< orphan*/ * DictionaryListObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dict_key ; 

__attribute__((used)) static PyObject *
DictionaryListKeys(DictionaryObject *self)
{
    return DictionaryListObjects(self, dict_key);
}