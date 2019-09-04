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
typedef  int uint64_t ;
struct TYPE_2__ {char* sct_text_file; int /*<<< orphan*/  sct_dir; int /*<<< orphan*/  sct_list; } ;
typedef  int /*<<< orphan*/  SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_LOG_ENTRY_TYPE_X509 ; 
 int /*<<< orphan*/  EXECUTE_CT_TEST () ; 
 int /*<<< orphan*/  SCT_VERSION_V1 ; 
 int /*<<< orphan*/ * SCT_new_from_base64 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int const,char const*,char const*) ; 
 int /*<<< orphan*/  SETUP_CT_TEST_FIXTURE () ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_dir ; 
 TYPE_1__* fixture ; 
 int result ; 
 int /*<<< orphan*/  sk_SCT_new_null () ; 
 int /*<<< orphan*/  sk_SCT_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_encode_tls_sct(void)
{
    const char log_id[] = "3xwuwRUAlFJHqWFoMl3cXHlZ6PfG04j8AC4LvT9012Q=";
    const uint64_t timestamp = 1;
    const char extensions[] = "";
    const char signature[] = "BAMARzBAMiBIL2dRrzXbplQ2vh/WZA89v5pBQpSVkkUwKI+j5"
            "eI+BgIhAOTtwNs6xXKx4vXoq2poBlOYfc9BAn3+/6EFUZ2J7b8I";
    SCT *sct = NULL;

    SETUP_CT_TEST_FIXTURE();
    if (fixture == NULL)
        return 0;

    fixture->sct_list = sk_SCT_new_null();
    if (!TEST_ptr(sct = SCT_new_from_base64(SCT_VERSION_V1, log_id,
                                            CT_LOG_ENTRY_TYPE_X509, timestamp,
                                            extensions, signature)))

        return 0;

    sk_SCT_push(fixture->sct_list, sct);
    fixture->sct_dir = ct_dir;
    fixture->sct_text_file = "tls1.sct";
    EXECUTE_CT_TEST();
    return result;
}