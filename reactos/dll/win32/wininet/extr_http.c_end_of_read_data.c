#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* data_stream; int /*<<< orphan*/  read_size; } ;
typedef  TYPE_2__ http_request_t ;
struct TYPE_8__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {scalar_t__ (* end_of_data ) (TYPE_3__*,TYPE_2__*) ;} ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static BOOL end_of_read_data( http_request_t *req )
{
    return !req->read_size && req->data_stream->vtbl->end_of_data(req->data_stream, req);
}