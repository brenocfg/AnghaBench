#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* dict; } ;
struct TYPE_5__ {scalar_t__ ht_used; } ;
struct TYPE_6__ {TYPE_1__ dv_hashtab; } ;
typedef  int /*<<< orphan*/  PyInt ;
typedef  TYPE_3__ DictionaryObject ;

/* Variables and functions */

__attribute__((used)) static PyInt
DictionaryLength(DictionaryObject *self)
{
    return ((PyInt) (self->dict->dv_hashtab.ht_used));
}