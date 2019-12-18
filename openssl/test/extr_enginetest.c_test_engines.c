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
typedef  int /*<<< orphan*/  block ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_get_first () ; 
 int /*<<< orphan*/  ENGINE_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_new () ; 
 int /*<<< orphan*/  ENGINE_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int NUMTOADD ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char*) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_engine_list () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  test_note (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_engines(void)
{
    ENGINE *block[NUMTOADD];
    char *eid[NUMTOADD];
    char *ename[NUMTOADD];
    char buf[256];
    ENGINE *ptr;
    int loop;
    int to_return = 0;
    ENGINE *new_h1 = NULL;
    ENGINE *new_h2 = NULL;
    ENGINE *new_h3 = NULL;
    ENGINE *new_h4 = NULL;

    memset(block, 0, sizeof(block));
    if (!TEST_ptr(new_h1 = ENGINE_new())
            || !TEST_true(ENGINE_set_id(new_h1, "test_id0"))
            || !TEST_true(ENGINE_set_name(new_h1, "First test item"))
            || !TEST_ptr(new_h2 = ENGINE_new())
            || !TEST_true(ENGINE_set_id(new_h2, "test_id1"))
            || !TEST_true(ENGINE_set_name(new_h2, "Second test item"))
            || !TEST_ptr(new_h3 = ENGINE_new())
            || !TEST_true(ENGINE_set_id(new_h3, "test_id2"))
            || !TEST_true(ENGINE_set_name(new_h3, "Third test item"))
            || !TEST_ptr(new_h4 = ENGINE_new())
            || !TEST_true(ENGINE_set_id(new_h4, "test_id3"))
            || !TEST_true(ENGINE_set_name(new_h4, "Fourth test item")))
        goto end;
    TEST_info("Engines:");
    display_engine_list();

    if (!TEST_true(ENGINE_add(new_h1)))
        goto end;
    TEST_info("Engines:");
    display_engine_list();

    ptr = ENGINE_get_first();
    if (!TEST_true(ENGINE_remove(ptr)))
        goto end;
    ENGINE_free(ptr);
    TEST_info("Engines:");
    display_engine_list();

    if (!TEST_true(ENGINE_add(new_h3))
            || !TEST_true(ENGINE_add(new_h2)))
        goto end;
    TEST_info("Engines:");
    display_engine_list();

    if (!TEST_true(ENGINE_remove(new_h2)))
        goto end;
    TEST_info("Engines:");
    display_engine_list();

    if (!TEST_true(ENGINE_add(new_h4)))
        goto end;
    TEST_info("Engines:");
    display_engine_list();

    /* Should fail. */
    if (!TEST_false(ENGINE_add(new_h3)))
        goto end;
    ERR_clear_error();

    /* Should fail. */
    if (!TEST_false(ENGINE_remove(new_h2)))
        goto end;
    ERR_clear_error();

    if (!TEST_true(ENGINE_remove(new_h3)))
        goto end;
    TEST_info("Engines:");
    display_engine_list();

    if (!TEST_true(ENGINE_remove(new_h4)))
        goto end;
    TEST_info("Engines:");
    display_engine_list();

    /*
     * At this point, we should have an empty list, unless some hardware
     * support engine got added.  However, since we don't allow the config
     * file to be loaded and don't otherwise load any built in engines,
     * that is unlikely.  Still, we check, if for nothing else, then to
     * notify that something is a little off (and might mean that |new_h1|
     * wasn't unloaded when it should have)
     */
    if ((ptr = ENGINE_get_first()) != NULL) {
        if (!ENGINE_remove(ptr))
            TEST_info("Remove failed - probably no hardware support present");
    }
    ENGINE_free(ptr);
    TEST_info("Engines:");
    display_engine_list();

    if (!TEST_true(ENGINE_add(new_h1))
            || !TEST_true(ENGINE_remove(new_h1)))
        goto end;

    TEST_info("About to beef up the engine-type list");
    for (loop = 0; loop < NUMTOADD; loop++) {
        sprintf(buf, "id%d", loop);
        eid[loop] = OPENSSL_strdup(buf);
        sprintf(buf, "Fake engine type %d", loop);
        ename[loop] = OPENSSL_strdup(buf);
        if (!TEST_ptr(block[loop] = ENGINE_new())
                || !TEST_true(ENGINE_set_id(block[loop], eid[loop]))
                || !TEST_true(ENGINE_set_name(block[loop], ename[loop])))
            goto end;
    }
    for (loop = 0; loop < NUMTOADD; loop++) {
        if (!TEST_true(ENGINE_add(block[loop]))) {
            test_note("Adding stopped at %d, (%s,%s)",
                      loop, ENGINE_get_id(block[loop]),
                      ENGINE_get_name(block[loop]));
            goto cleanup_loop;
        }
    }
 cleanup_loop:
    TEST_info("About to empty the engine-type list");
    while ((ptr = ENGINE_get_first()) != NULL) {
        if (!TEST_true(ENGINE_remove(ptr)))
            goto end;
        ENGINE_free(ptr);
    }
    for (loop = 0; loop < NUMTOADD; loop++) {
        OPENSSL_free(eid[loop]);
        OPENSSL_free(ename[loop]);
    }
    to_return = 1;

 end:
    ENGINE_free(new_h1);
    ENGINE_free(new_h2);
    ENGINE_free(new_h3);
    ENGINE_free(new_h4);
    for (loop = 0; loop < NUMTOADD; loop++)
        ENGINE_free(block[loop]);
    return to_return;
}