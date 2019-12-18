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
typedef  int /*<<< orphan*/  utf8leaf_t ;
struct unicode_data {scalar_t__ correction; int gen; int code; scalar_t__* utf8nfdi; char* utf8nfdicf; scalar_t__ ccc; } ;
struct tree {char* type; int maxage; } ;

/* Variables and functions */
 scalar_t__ DECOMPOSE ; 
 scalar_t__ HANGUL ; 
 scalar_t__ HANGUL_SYLLABLE (int) ; 
 scalar_t__ LEAF_CCC (int /*<<< orphan*/ *) ; 
 int LEAF_GEN (int /*<<< orphan*/ *) ; 
 char* LEAF_STR (int /*<<< orphan*/ *) ; 
 int UTF8HANGULLEAF ; 
 struct unicode_data* corrections_lookup (struct unicode_data*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strcmp (char*,char*) ; 
 struct unicode_data* unicode_data ; 
 int /*<<< orphan*/  utf8encode (char*,unsigned int) ; 
 int /*<<< orphan*/ * utf8lookup (struct tree*,unsigned char*,char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void verify(struct tree *tree)
{
	struct unicode_data *data;
	utf8leaf_t	*leaf;
	unsigned int	unichar;
	char		key[4];
	unsigned char	hangul[UTF8HANGULLEAF];
	int		report;
	int		nocf;

	if (verbose > 0)
		printf("Verifying %s_%x\n", tree->type, tree->maxage);
	nocf = strcmp(tree->type, "nfdicf");

	for (unichar = 0; unichar != 0x110000; unichar++) {
		report = 0;
		data = corrections_lookup(&unicode_data[unichar]);
		if (data->correction <= tree->maxage)
			data = &unicode_data[unichar];
		utf8encode(key,unichar);
		leaf = utf8lookup(tree, hangul, key);

		if (!leaf) {
			if (data->gen != -1)
				report++;
			if (unichar < 0xd800 || unichar > 0xdfff)
				report++;
		} else {
			if (unichar >= 0xd800 && unichar <= 0xdfff)
				report++;
			if (data->gen == -1)
				report++;
			if (data->gen != LEAF_GEN(leaf))
				report++;
			if (LEAF_CCC(leaf) == DECOMPOSE) {
				if (HANGUL_SYLLABLE(data->code)) {
					if (data->utf8nfdi[0] != HANGUL)
						report++;
				} else if (nocf) {
					if (!data->utf8nfdi) {
						report++;
					} else if (strcmp(data->utf8nfdi,
							  LEAF_STR(leaf))) {
						report++;
					}
				} else {
					if (!data->utf8nfdicf &&
					    !data->utf8nfdi) {
						report++;
					} else if (data->utf8nfdicf) {
						if (strcmp(data->utf8nfdicf,
							   LEAF_STR(leaf)))
							report++;
					} else if (strcmp(data->utf8nfdi,
							  LEAF_STR(leaf))) {
						report++;
					}
				}
			} else if (data->ccc != LEAF_CCC(leaf)) {
				report++;
			}
		}
		if (report) {
			printf("%X code %X gen %d ccc %d"
				" nfdi -> \"%s\"",
				unichar, data->code, data->gen,
				data->ccc,
				data->utf8nfdi);
			if (leaf) {
				printf(" gen %d ccc %d"
					" nfdi -> \"%s\"",
					LEAF_GEN(leaf),
					LEAF_CCC(leaf),
					LEAF_CCC(leaf) == DECOMPOSE ?
						LEAF_STR(leaf) : "");
			}
			printf("\n");
		}
	}
}