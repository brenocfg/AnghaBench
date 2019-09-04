#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlBufferPtr ;
struct TYPE_17__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ smart_str ;
typedef  TYPE_4__* sdlTypePtr ;
typedef  int /*<<< orphan*/  encodeTypePtr ;
struct TYPE_18__ {scalar_t__ encode; } ;
struct TYPE_16__ {scalar_t__ name; TYPE_1__* ns; } ;
struct TYPE_15__ {scalar_t__ href; } ;
struct TYPE_14__ {scalar_t__ elements; } ;

/* Variables and functions */
 TYPE_13__* SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * master_to_zval_int (int /*<<< orphan*/ *,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  sdl ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_3__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_3__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_3__*) ; 
 scalar_t__ xmlBufferContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlNodeDump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* zend_hash_find_ptr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zval *to_zval_any(zval *ret, encodeTypePtr type, xmlNodePtr data)
{
	xmlBufferPtr buf;

	if (SOAP_GLOBAL(sdl) && SOAP_GLOBAL(sdl)->elements && data->name) {
		smart_str nscat = {0};
		sdlTypePtr sdl_type;

		if (data->ns && data->ns->href) {
			smart_str_appends(&nscat, (char*)data->ns->href);
			smart_str_appendc(&nscat, ':');
		}
		smart_str_appends(&nscat, (char*)data->name);
		smart_str_0(&nscat);

		if ((sdl_type = zend_hash_find_ptr(SOAP_GLOBAL(sdl)->elements, nscat.s)) != NULL &&
		    sdl_type->encode) {
			smart_str_free(&nscat);
			return master_to_zval_int(ret, sdl_type->encode, data);
		}
		smart_str_free(&nscat);
	}

	buf = xmlBufferCreate();
	xmlNodeDump(buf, NULL, data, 0, 0);
	ZVAL_STRING(ret, (char*)xmlBufferContent(buf));
	xmlBufferFree(buf);
	return ret;
}