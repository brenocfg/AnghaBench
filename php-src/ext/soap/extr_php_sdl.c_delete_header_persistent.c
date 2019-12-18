#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_1__* sdlSoapBindingFunctionHeaderPtr ;
struct TYPE_5__ {struct TYPE_5__* headerfaults; struct TYPE_5__* ns; struct TYPE_5__* name; } ;

/* Variables and functions */
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_1__*) ; 

__attribute__((used)) static void delete_header_persistent(zval *zv)
{
	sdlSoapBindingFunctionHeaderPtr hdr = Z_PTR_P(zv);
	if (hdr->name) {
		free(hdr->name);
	}
	if (hdr->ns) {
		free(hdr->ns);
	}
	if (hdr->headerfaults) {
		zend_hash_destroy(hdr->headerfaults);
		free(hdr->headerfaults);
	}
	free(hdr);
}