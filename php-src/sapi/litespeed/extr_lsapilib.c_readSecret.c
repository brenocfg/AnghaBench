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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  lsapi_log (char*,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ,int) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_secret ; 

__attribute__((used)) static int readSecret( const char * pSecretFile )
{
    struct stat st;
    int fd = open( pSecretFile, O_RDONLY , 0600 );
    if ( fd == -1 )
    {
        lsapi_log("LSAPI: failed to open secret file: %s!\n", pSecretFile );
        return -1;
    }
    if ( fstat( fd, &st ) == -1 )
    {
        lsapi_log("LSAPI: failed to check state of file: %s!\n", pSecretFile );
        close( fd );
        return -1;
    }
/*
    if ( st.st_uid != s_uid )
    {
        lsapi_log("LSAPI: file owner check failure: %s!\n", pSecretFile );
        close( fd );
        return -1;
    }
*/
    if ( st.st_mode & 0077 )
    {
        lsapi_log("LSAPI: file permission check failure: %s\n", pSecretFile );
        close( fd );
        return -1;
    }
    if ( read( fd, s_secret, 16 ) < 16 )
    {
        lsapi_log("LSAPI: failed to read secret from secret file: %s\n", pSecretFile );
        close( fd );
        return -1;
    }
    close( fd );
    return 0;
}