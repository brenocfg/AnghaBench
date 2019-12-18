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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int ignore_php_ini ; 
 int source_highlight ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_opt( int argc, char * argv[], int *climode,
                        char **php_ini_path, char ** php_bind )
{
    char ** p = &argv[1];
    char ** argend= &argv[argc];
    int c;
    while (( p < argend )&&(**p == '-' )) {
        c = *((*p)+1);
        ++p;
        switch( c ) {
        case 'b':
            if ( p >= argend ) {
                fprintf( stderr, "TCP or socket address must be specified following '-b' option.\n");
                return -1;
            }
            *php_bind = strdup(*p++);
            break;

        case 'c':
            if ( p >= argend ) {
                fprintf( stderr, "<path> or <file> must be specified following '-c' option.\n");

                return -1;
            }
            *php_ini_path = strdup( *p++ );
            break;
        case 's':
            source_highlight = 1;
            break;
        case 'n':
            ignore_php_ini = 1;
            break;
        case '?':
            if ( *((*(p-1))+2) == 's' )
                exit( 99 );
        case 'h':
        case 'i':
        case 'l':
        case 'q':
        case 'v':
        default:
            *climode = 1;
            break;
        }
    }
    if ( p - argv < argc ) {
        *climode = 1;
    }
    return 0;
}