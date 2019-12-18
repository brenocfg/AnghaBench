#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ content_read; scalar_t__ content_length; } ;
typedef  TYPE_1__ netconn_stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  netconn; } ;
typedef  TYPE_2__ http_request_t ;
typedef  int /*<<< orphan*/  data_stream_t ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  is_valid_netconn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL netconn_end_of_data(data_stream_t *stream, http_request_t *req)
{
    netconn_stream_t *netconn_stream = (netconn_stream_t*)stream;
    return netconn_stream->content_read == netconn_stream->content_length || !is_valid_netconn(req->netconn);
}