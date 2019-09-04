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
typedef  int /*<<< orphan*/  X509_REQ ;
typedef  int /*<<< orphan*/  X509_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_REQ_set_subject_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_name (char const*,unsigned long,int) ; 

__attribute__((used)) static int build_subject(X509_REQ *req, const char *subject, unsigned long chtype,
                         int multirdn)
{
    X509_NAME *n;

    if ((n = parse_name(subject, chtype, multirdn)) == NULL)
        return 0;

    if (!X509_REQ_set_subject_name(req, n)) {
        X509_NAME_free(n);
        return 0;
    }
    X509_NAME_free(n);
    return 1;
}