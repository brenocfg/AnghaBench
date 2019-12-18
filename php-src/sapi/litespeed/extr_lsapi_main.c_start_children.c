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
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  getpgrp () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  litespeed_cleanup ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ s_stop ; 
 int /*<<< orphan*/  setsid () ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int wait (int*) ; 

void start_children( int children )
{
    struct sigaction act, old_term, old_quit, old_int, old_usr1;
    int running = 0;
    int status;
    pid_t pid;

    /* Create a process group */
    setsid();

    /* Set up handler to kill children upon exit */
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = litespeed_cleanup;
    if( sigaction( SIGTERM, &act, &old_term ) ||
        sigaction( SIGINT,  &act, &old_int  ) ||
        sigaction( SIGUSR1, &act, &old_usr1 ) ||
        sigaction( SIGQUIT, &act, &old_quit )) {
        perror( "Can't set signals" );
        exit( 1 );
    }
    s_stop = 0;
    while( 1 ) {
        while((!s_stop )&&( running < children )) {
            pid = fork();
            switch( pid ) {
            case 0: /* children process */

                /* don't catch our signals */
                sigaction( SIGTERM, &old_term, 0 );
                sigaction( SIGQUIT, &old_quit, 0 );
                sigaction( SIGINT,  &old_int,  0 );
                sigaction( SIGUSR1, &old_usr1, 0 );
                return ;
            case -1:
                perror( "php (pre-forking)" );
                exit( 1 );
                break;
            default: /* parent process */
                running++;
                break;
            }
        }
        if ( s_stop ) {
            break;
        }
        pid = wait( &status );
        running--;
    }
    kill( -getpgrp(), SIGUSR1 );
    exit( 0 );
}