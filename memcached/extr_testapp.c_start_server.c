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
typedef  int /*<<< orphan*/  tmo ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  pid_file ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ in_port_t ;
typedef  int /*<<< orphan*/  environment ;
typedef  int /*<<< orphan*/  coreadm ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ enable_ssl ; 
 int /*<<< orphan*/  errno ; 
 int execv (char*,char**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getpid () ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  putenv (char*) ; 
 scalar_t__ remove (char*) ; 
 int safe_strtol (char*,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static pid_t start_server(in_port_t *port_out, bool daemon, int timeout) {
    char environment[80];
    snprintf(environment, sizeof(environment),
             "MEMCACHED_PORT_FILENAME=/tmp/ports.%lu", (long)getpid());
    char *filename= environment + strlen("MEMCACHED_PORT_FILENAME=");
    char pid_file[80];
    snprintf(pid_file, sizeof(pid_file), "/tmp/pid.%lu", (long)getpid());

    remove(filename);
    remove(pid_file);

#ifdef __sun
    /* I want to name the corefiles differently so that they don't
       overwrite each other
    */
    char coreadm[128];
    snprintf(coreadm, sizeof(coreadm),
             "coreadm -p core.%%f.%%p %lu", (unsigned long)getpid());
    system(coreadm);
#endif

    pid_t pid = fork();
    assert(pid != -1);

    if (pid == 0) {
        /* Child */
        char *argv[24];
        int arg = 0;
        char tmo[24];
        snprintf(tmo, sizeof(tmo), "%u", timeout);

        putenv(environment);
#ifdef __sun
        putenv("LD_PRELOAD=watchmalloc.so.1");
        putenv("MALLOC_DEBUG=WATCH");
#endif

        if (!daemon) {
            argv[arg++] = "./timedrun";
            argv[arg++] = tmo;
        }
        argv[arg++] = "./memcached-debug";
        argv[arg++] = "-A";
        argv[arg++] = "-p";
        argv[arg++] = "-1";
        argv[arg++] = "-U";
        argv[arg++] = "0";
#ifdef TLS
        if (enable_ssl) {
            argv[arg++] = "-Z";
            argv[arg++] = "-o";
            argv[arg++] = "ssl_chain_cert=t/server_crt.pem";
            argv[arg++] = "-o";
            argv[arg++] = "ssl_key=t/server_key.pem";
        }
#endif
        /* Handle rpmbuild and the like doing this as root */
        if (getuid() == 0) {
            argv[arg++] = "-u";
            argv[arg++] = "root";
        }
        if (daemon) {
            argv[arg++] = "-d";
            argv[arg++] = "-P";
            argv[arg++] = pid_file;
        }
#ifdef MESSAGE_DEBUG
         argv[arg++] = "-vvv";
#endif
#ifdef HAVE_DROP_PRIVILEGES
        argv[arg++] = "-o";
        argv[arg++] = "relaxed_privileges";
#endif
        argv[arg++] = NULL;
        assert(execv(argv[0], argv) != -1);
    }

    /* Yeah just let us "busy-wait" for the file to be created ;-) */
    while (access(filename, F_OK) == -1) {
        usleep(10);
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open the file containing port numbers: %s\n",
                strerror(errno));
        assert(false);
    }

    *port_out = (in_port_t)-1;
    char buffer[80];
    while ((fgets(buffer, sizeof(buffer), fp)) != NULL) {
        if (strncmp(buffer, "TCP INET: ", 10) == 0) {
            int32_t val;
            assert(safe_strtol(buffer + 10, &val));
            *port_out = (in_port_t)val;
        }
    }
    fclose(fp);
    assert(remove(filename) == 0);

    if (daemon) {
        /* loop and wait for the pid file.. There is a potential race
         * condition that the server just created the file but isn't
         * finished writing the content, so we loop a few times
         * reading as well */
        while (access(pid_file, F_OK) == -1) {
            usleep(10);
        }

        fp = fopen(pid_file, "r");
        if (fp == NULL) {
            fprintf(stderr, "Failed to open pid file: %s\n",
                    strerror(errno));
            assert(false);
        }

        /* Avoid race by retrying 20 times */
        for (int x = 0; x < 20 && fgets(buffer, sizeof(buffer), fp) == NULL; x++) {
            usleep(10);
        }
        fclose(fp);

        int32_t val;
        assert(safe_strtol(buffer, &val));
        pid = (pid_t)val;
    }

    return pid;
}