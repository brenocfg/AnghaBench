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
struct TYPE_7__ {scalar_t__ type_info; int /*<<< orphan*/  (* free_ ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  types; } ;
struct TYPE_5__ {TYPE_3__ type_data; } ;
typedef  TYPE_1__ SType ;
typedef  TYPE_2__ STpiStream ;
typedef  int /*<<< orphan*/  RListIter ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 scalar_t__ r_list_iter_get (int /*<<< orphan*/ *) ; 
 scalar_t__ r_list_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_iterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void free_tpi_stream(void *stream) {
	STpiStream *tpi_stream = (STpiStream *)stream;
	RListIter *it;
	SType *type = NULL;

	it = r_list_iterator (tpi_stream->types);
	while (r_list_iter_next (it)) {
		type = (SType *) r_list_iter_get (it);
		if (!type) {
			continue;
		}
		if (type->type_data.free_) {
			type->type_data.free_ (&type->type_data);
			type->type_data.free_ = 0;
		}
		if (type->type_data.type_info) {
			free (type->type_data.type_info);
			type->type_data.free_ = 0;
			type->type_data.type_info = 0;
		}
		R_FREE (type);
	}
	r_list_free (tpi_stream->types);
}