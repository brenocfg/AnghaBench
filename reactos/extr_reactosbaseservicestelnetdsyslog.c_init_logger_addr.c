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
struct hostent {int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  host ;
struct TYPE_5__ {int /*<<< orphan*/  S_addr; } ;
struct TYPE_6__ {TYPE_1__ S_un; int /*<<< orphan*/  s_addr; } ;
struct TYPE_7__ {void* sin_port; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  SOCKADDR_IN ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int FILENAME_MAX ; 
 unsigned short SYSLOG_PORT ; 
 char** __argv ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ sa_logger ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* syslog_conf_dir ; 

__attribute__((used)) static void init_logger_addr()
{
    char pathname[ FILENAME_MAX ];
    char *p;
    FILE *fd;
    char host[256];
    struct hostent * phe;

    memset( &sa_logger, 0, sizeof(SOCKADDR_IN) );
    sa_logger.sin_family = AF_INET;

    if( '\\' == syslog_conf_dir[0] || '/' == syslog_conf_dir[0] || ':' == syslog_conf_dir[1] )
    {
        /* absolute path */
        strcpy( pathname, syslog_conf_dir );
    }
    else
    {
        /* relative path */
        char *q;

        strcpy( pathname, __argv[0] );
        p = strrchr( pathname, '\\' ) + 1;
        q = strrchr( pathname, '/' ) + 1;
        if( p < q )
            *q = 0;
        else if( p > q )
            *p = 0;
        else
            pathname[0] = 0;
        strcat( pathname, syslog_conf_dir );
    }
    p = &pathname[ strlen( pathname ) - 1 ];
    if( '\\' != *p && '/' != *p )
    {
        p++; *p = '/';
    }
    strcpy( ++p, "syslog.host" );

    /* read destination host name */
    fd = fopen( pathname, "r" );
    if( !fd )
        goto use_default;

    if( NULL == fgets( host, sizeof(host), fd ) )
        host[0] = 0;
    else
    {
        p = strchr( host, '\n' );
        if( p )
            *p = 0;
        p = strchr( host, '\r' );
        if( p )
            *p = 0;
    }
    fclose( fd );

    p = strchr( host, ':' );
    if( p )
        *p++ = 0;

    phe = gethostbyname( host );
    if( !phe )
        goto use_default;

    memcpy( &sa_logger.sin_addr.s_addr, phe->h_addr, phe->h_length );

    if( p )
        sa_logger.sin_port = htons( (unsigned short) strtoul( p, NULL, 0 ) );
    else
        sa_logger.sin_port = htons( SYSLOG_PORT );
    return;

use_default:
    sa_logger.sin_addr.S_un.S_addr = htonl( 0x7F000001 );
    sa_logger.sin_port = htons( SYSLOG_PORT );
}