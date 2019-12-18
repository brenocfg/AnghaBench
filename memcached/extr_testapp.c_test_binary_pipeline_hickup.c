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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  enum test_return { ____Placeholder_test_return } test_return ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_CMD_QUITQ ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 int allow_closed_read ; 
 int /*<<< orphan*/  binary_hickup_recv_verification_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int hickup_thread_running ; 
 void* malloc (size_t) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t raw_command (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_send (void*,size_t,int) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  test_binary_pipeline_hickup_chunk (void*,size_t) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static enum test_return test_binary_pipeline_hickup(void)
{
    size_t buffersize = 65 * 1024;
    void *buffer = malloc(buffersize);
    int ii;

    pthread_t tid;
    int ret;
    allow_closed_read = true;
    hickup_thread_running = true;
    if ((ret = pthread_create(&tid, NULL,
                              binary_hickup_recv_verification_thread, NULL)) != 0) {
        fprintf(stderr, "Can't create thread: %s\n", strerror(ret));
        free(buffer);
        return TEST_FAIL;
    }

    /* Allow the thread to start */
    usleep(250);

    srand((int)time(NULL));
    for (ii = 0; ii < 2; ++ii) {
        test_binary_pipeline_hickup_chunk(buffer, buffersize);
    }

    /* send quitq to shut down the read thread ;-) */
    size_t len = raw_command(buffer, buffersize, PROTOCOL_BINARY_CMD_QUITQ,
                             NULL, 0, NULL, 0);
    safe_send(buffer, len, false);

    pthread_join(tid, NULL);
    free(buffer);
    return TEST_PASS;
}