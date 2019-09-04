#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_10__ {int /*<<< orphan*/ * stats; int /*<<< orphan*/ * vio; TYPE_3__* protocol_frame_codec; int /*<<< orphan*/ * error_info; } ;
struct TYPE_9__ {TYPE_2__* data; } ;
struct TYPE_7__ {size_t (* send ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_1__ m; } ;
typedef  int /*<<< orphan*/  MYSQLND_VIO ;
typedef  int /*<<< orphan*/  MYSQLND_STATS ;
typedef  TYPE_3__ MYSQLND_PFC ;
typedef  int /*<<< orphan*/  MYSQLND_ERROR_INFO ;
typedef  TYPE_4__ MYSQLND_CONN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (size_t) ; 
 int MYSQLND_HEADER_SIZE ; 
 int /*<<< orphan*/  int1store (int /*<<< orphan*/ *,char) ; 
 size_t stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
size_t php_mysqlnd_sha256_pk_request_write(MYSQLND_CONN_DATA * conn, void * _packet)
{
	MYSQLND_ERROR_INFO * error_info = conn->error_info;
	MYSQLND_PFC * pfc = conn->protocol_frame_codec;
	MYSQLND_VIO * vio = conn->vio;
	MYSQLND_STATS * stats = conn->stats;
	zend_uchar buffer[MYSQLND_HEADER_SIZE + 1];
	size_t sent;

	DBG_ENTER("php_mysqlnd_sha256_pk_request_write");

	int1store(buffer + MYSQLND_HEADER_SIZE, '\1');
	sent = pfc->data->m.send(pfc, vio, buffer, 1, stats, error_info);

	DBG_RETURN(sent);
}