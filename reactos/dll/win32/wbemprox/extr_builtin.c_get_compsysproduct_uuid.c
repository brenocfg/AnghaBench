#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  compsysproduct_uuidW ; 
 int /*<<< orphan*/  gethostuuid (unsigned char*,struct timespec const*) ; 
 char* heap_alloc (int) ; 
 char* heap_strdupW (int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 char toupperW (unsigned char) ; 

__attribute__((used)) static WCHAR *get_compsysproduct_uuid(void)
{
#ifdef __APPLE__
    unsigned char uuid[16];
    const struct timespec timeout = {1, 0};
    if (!gethostuuid( uuid, &timeout ))
    {
        static const WCHAR fmtW[] =
            {'%','0','2','X','%','0','2','X','%','0','2','X','%','0','2','X','-','%','0','2','X','%','0','2','X','-',
             '%','0','2','X','%','0','2','X','-','%','0','2','X','%','0','2','X','-','%','0','2','X','%','0','2','X',
             '%','0','2','X','%','0','2','X','%','0','2','X','%','0','2','X',0};
        WCHAR *ret = heap_alloc( 37 * sizeof(WCHAR) );
        if (!ret) return NULL;
        sprintfW( ret, fmtW, uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7],
                  uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15] );
        return ret;
    }
#endif
#ifdef __linux__
    int file;
    if ((file = open( "/var/lib/dbus/machine-id", O_RDONLY )) != -1)
    {
        unsigned char buf[32];
        if (read( file, buf, sizeof(buf) ) == sizeof(buf))
        {
            unsigned int i, j;
            WCHAR *ret, *p;

            close( file );
            if (!(p = ret = heap_alloc( 37 * sizeof(WCHAR) ))) return NULL;
            for (i = 0, j = 0; i < 8; i++) p[i] = toupperW( buf[j++] );
            p[8] = '-';
            for (i = 9; i < 13; i++) p[i] = toupperW( buf[j++] );
            p[13] = '-';
            for (i = 14; i < 18; i++) p[i] = toupperW( buf[j++] );
            p[18] = '-';
            for (i = 19; i < 23; i++) p[i] = toupperW( buf[j++] );
            p[23] = '-';
            for (i = 24; i < 36; i++) p[i] = toupperW( buf[j++] );
            ret[i] = 0;
            return ret;
        }
        close( file );
    }
#endif
    return heap_strdupW( compsysproduct_uuidW );
}