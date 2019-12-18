#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  char xmlChar ;
typedef  int /*<<< orphan*/ * sdlTypePtr ;
typedef  TYPE_3__* sdlPtr ;
struct TYPE_10__ {scalar_t__ elements; } ;
struct TYPE_9__ {int /*<<< orphan*/  doc; } ;
struct TYPE_8__ {char const* href; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  parse_namespace (char const*,char**,char**) ; 
 int strlen (char*) ; 
 TYPE_1__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int xmlStrlen (char const*) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (scalar_t__,char*,int) ; 

__attribute__((used)) static sdlTypePtr get_element(sdlPtr sdl, xmlNodePtr node, const xmlChar *type)
{
	sdlTypePtr ret = NULL;

	if (sdl->elements) {
		xmlNsPtr nsptr;
		char *ns, *cptype;
		sdlTypePtr sdl_type;

		parse_namespace(type, &cptype, &ns);
		nsptr = xmlSearchNs(node->doc, node, BAD_CAST(ns));
		if (nsptr != NULL) {
			int ns_len = xmlStrlen(nsptr->href);
			int type_len = strlen(cptype);
			int len = ns_len + type_len + 1;
			char *nscat = emalloc(len + 1);

			memcpy(nscat, nsptr->href, ns_len);
			nscat[ns_len] = ':';
			memcpy(nscat+ns_len+1, cptype, type_len);
			nscat[len] = '\0';

			if ((sdl_type = zend_hash_str_find_ptr(sdl->elements, nscat, len)) != NULL) {
				ret = sdl_type;
			} else if ((sdl_type = zend_hash_str_find_ptr(sdl->elements, (char*)type, type_len)) != NULL) {
				ret = sdl_type;
			}
			efree(nscat);
		} else {
			if ((sdl_type = zend_hash_str_find_ptr(sdl->elements, (char*)type, xmlStrlen(type))) != NULL) {
				ret = sdl_type;
			}
		}

		efree(cptype);
		if (ns) {efree(ns);}
	}
	return ret;
}