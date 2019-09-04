#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fd; } ;
struct TYPE_7__ {int /*<<< orphan*/ * opened_path; scalar_t__ free_filename; scalar_t__ filename; TYPE_1__ handle; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_file_handle ;
struct TYPE_8__ {scalar_t__ path_translated; } ;

/* Variables and functions */
 TYPE_5__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_HANDLE_FILENAME ; 
 char* argv0 ; 
 int /*<<< orphan*/  memccpy (char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_execute_script (TYPE_2__*) ; 
 int /*<<< orphan*/  request_info ; 
 int strlen (scalar_t__) ; 

__attribute__((used)) static int lsapi_execute_script( zend_file_handle * file_handle)
{
    char *p;
    int len;
    file_handle->type = ZEND_HANDLE_FILENAME;
    file_handle->handle.fd = 0;
    file_handle->filename = SG(request_info).path_translated;
    file_handle->free_filename = 0;
    file_handle->opened_path = NULL;

    p = argv0;
    *p++ = ':';
    len = strlen( SG(request_info).path_translated );
    if ( len > 45 )
        len = len - 45;
    else
        len = 0;
    memccpy( p, SG(request_info).path_translated + len, 0, 46 );

    php_execute_script(file_handle);
    return 0;

}