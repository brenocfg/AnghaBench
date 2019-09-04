#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  sdlPtr ;
typedef  int /*<<< orphan*/ * encodePtr ;
struct TYPE_7__ {int /*<<< orphan*/  doc; } ;
struct TYPE_6__ {scalar_t__ href; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/ * get_encoder (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * get_encoder_ex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_namespace (int /*<<< orphan*/  const*,char**,char**) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlStrlen (int /*<<< orphan*/  const*) ; 

encodePtr get_encoder_from_prefix(sdlPtr sdl, xmlNodePtr node, const xmlChar *type)
{
	encodePtr enc = NULL;
	xmlNsPtr nsptr;
	char *ns, *cptype;

	parse_namespace(type, &cptype, &ns);
	nsptr = xmlSearchNs(node->doc, node, BAD_CAST(ns));
	if (nsptr != NULL) {
		enc = get_encoder(sdl, (char*)nsptr->href, cptype);
		if (enc == NULL) {
			enc = get_encoder_ex(sdl, cptype, strlen(cptype));
		}
	} else {
		enc = get_encoder_ex(sdl, (char*)type, xmlStrlen(type));
	}
	efree(cptype);
	if (ns) {efree(ns);}
	return enc;
}