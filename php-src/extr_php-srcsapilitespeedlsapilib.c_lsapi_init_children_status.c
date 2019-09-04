#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsapi_child_status ;
struct TYPE_2__ {int m_iMaxChildren; int m_iExtraChildren; int /*<<< orphan*/ * m_pChildrenStatusEnd; int /*<<< orphan*/ * m_pChildrenStatusCur; int /*<<< orphan*/ * m_pChildrenStatus; } ;

/* Variables and functions */
 int MAP_ANON ; 
 char* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 TYPE_1__* g_prefork_server ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int* s_accepting_workers ; 
 size_t* s_avail_pages ; 
 int* s_busy_workers ; 
 int* s_global_counter ; 

__attribute__((used)) static int lsapi_init_children_status(void)
{
    int size = 4096;
    int max_children = g_prefork_server->m_iMaxChildren
                        + g_prefork_server->m_iExtraChildren;

    char * pBuf;
    size = max_children * sizeof( lsapi_child_status ) * 2 + 3 * sizeof(int);
    size = (size + 4095) / 4096 * 4096;
    pBuf =( char*) mmap( NULL, size, PROT_READ | PROT_WRITE,
        MAP_ANON | MAP_SHARED, -1, 0 );
    if ( pBuf == MAP_FAILED )
    {
        perror( "Anonymous mmap() failed" );
        return -1;
    }
    memset( pBuf, 0, size );
    g_prefork_server->m_pChildrenStatus = (lsapi_child_status *)pBuf;
    g_prefork_server->m_pChildrenStatusCur = (lsapi_child_status *)pBuf;
    g_prefork_server->m_pChildrenStatusEnd = (lsapi_child_status *)pBuf + max_children;
    s_busy_workers = (int *)g_prefork_server->m_pChildrenStatusEnd;
    s_accepting_workers = s_busy_workers + 1;
    s_global_counter = s_accepting_workers + 1;
    s_avail_pages = (size_t *)(s_global_counter + 1);
    return 0;
}