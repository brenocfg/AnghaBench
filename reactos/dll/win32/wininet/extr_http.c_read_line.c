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
struct TYPE_5__ {int read_pos; int read_size; int /*<<< orphan*/  read_section; int /*<<< orphan*/ * read_buf; } ;
typedef  TYPE_1__ http_request_t ;
typedef  char* LPSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int read_more_data (TYPE_1__*,int) ; 
 int /*<<< orphan*/  remove_data (TYPE_1__*,int) ; 

__attribute__((used)) static DWORD read_line( http_request_t *req, LPSTR buffer, DWORD *len )
{
    int count, bytes_read, pos = 0;
    DWORD res;

    EnterCriticalSection( &req->read_section );
    for (;;)
    {
        BYTE *eol = memchr( req->read_buf + req->read_pos, '\n', req->read_size );

        if (eol)
        {
            count = eol - (req->read_buf + req->read_pos);
            bytes_read = count + 1;
        }
        else count = bytes_read = req->read_size;

        count = min( count, *len - pos );
        memcpy( buffer + pos, req->read_buf + req->read_pos, count );
        pos += count;
        remove_data( req, bytes_read );
        if (eol) break;

        if ((res = read_more_data( req, -1 )))
        {
            WARN( "read failed %u\n", res );
            LeaveCriticalSection( &req->read_section );
            return res;
        }
        if (!req->read_size)
        {
            *len = 0;
            TRACE( "returning empty string\n" );
            LeaveCriticalSection( &req->read_section );
            return ERROR_SUCCESS;
        }
    }
    LeaveCriticalSection( &req->read_section );

    if (pos < *len)
    {
        if (pos && buffer[pos - 1] == '\r') pos--;
        *len = pos + 1;
    }
    buffer[*len - 1] = 0;
    TRACE( "returning %s\n", debugstr_a(buffer));
    return ERROR_SUCCESS;
}