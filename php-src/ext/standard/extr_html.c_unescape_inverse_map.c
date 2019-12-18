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
typedef  int /*<<< orphan*/  entity_ht ;

/* Variables and functions */
#define  ENT_HTML_DOC_HTML401 130 
#define  ENT_HTML_DOC_HTML5 129 
 int ENT_HTML_DOC_TYPE_MASK ; 
#define  ENT_HTML_DOC_XHTML 128 
 int /*<<< orphan*/  const ent_ht_be_apos ; 
 int /*<<< orphan*/  const ent_ht_be_noapos ; 
 int /*<<< orphan*/  const ent_ht_html4 ; 
 int /*<<< orphan*/  const ent_ht_html5 ; 

__attribute__((used)) static const entity_ht *unescape_inverse_map(int all, int flags)
{
	int document_type = flags & ENT_HTML_DOC_TYPE_MASK;

	if (all) {
		switch (document_type) {
		case ENT_HTML_DOC_HTML401:
		case ENT_HTML_DOC_XHTML: /* but watch out for &apos;...*/
			return &ent_ht_html4;
		case ENT_HTML_DOC_HTML5:
			return &ent_ht_html5;
		default:
			return &ent_ht_be_apos;
		}
	} else {
		switch (document_type) {
		case ENT_HTML_DOC_HTML401:
			return &ent_ht_be_noapos;
		default:
			return &ent_ht_be_apos;
		}
	}
}