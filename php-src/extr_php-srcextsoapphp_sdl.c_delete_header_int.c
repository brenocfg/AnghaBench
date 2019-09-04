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
typedef  TYPE_1__* sdlSoapBindingFunctionHeaderPtr ;
struct TYPE_5__ {struct TYPE_5__* headerfaults; struct TYPE_5__* ns; struct TYPE_5__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (TYPE_1__*) ; 

__attribute__((used)) static void delete_header_int(sdlSoapBindingFunctionHeaderPtr hdr)
{
	if (hdr->name) {
		efree(hdr->name);
	}
	if (hdr->ns) {
		efree(hdr->ns);
	}
	if (hdr->headerfaults) {
		zend_hash_destroy(hdr->headerfaults);
		efree(hdr->headerfaults);
	}
	efree(hdr);
}