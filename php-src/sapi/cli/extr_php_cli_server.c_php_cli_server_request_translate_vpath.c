#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int st_mode; } ;
typedef  TYPE_1__ zend_stat_t ;
typedef  size_t uint32_t ;
struct TYPE_6__ {size_t vpath_len; char* vpath; size_t path_info_len; char* path_info; char* path_translated; int path_translated_len; TYPE_1__ sb; } ;
typedef  TYPE_2__ php_cli_server_request ;

/* Variables and functions */
 char DEFAULT_SLASH ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 int /*<<< orphan*/  pefree (char*,int) ; 
 void* pestrndup (char*,int,int) ; 
 int /*<<< orphan*/  php_sys_stat (char*,TYPE_1__*) ; 
 char* safe_pemalloc (int,size_t,int,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void php_cli_server_request_translate_vpath(php_cli_server_request *request, const char *document_root, size_t document_root_len) /* {{{ */
{
	zend_stat_t sb;
	static const char *index_files[] = { "index.php", "index.html", NULL };
	char *buf = safe_pemalloc(1, request->vpath_len, 1 + document_root_len + 1 + sizeof("index.html"), 1);
	char *p = buf, *prev_path = NULL, *q, *vpath;
	size_t prev_path_len = 0;
	int  is_static_file = 0;

	memmove(p, document_root, document_root_len);
	p += document_root_len;
	vpath = p;
	if (request->vpath_len > 0 && request->vpath[0] != '/') {
		*p++ = DEFAULT_SLASH;
	}
	q = request->vpath + request->vpath_len;
	while (q > request->vpath) {
		if (*q-- == '.') {
			is_static_file = 1;
			break;
		}
	}
	memmove(p, request->vpath, request->vpath_len);
#ifdef PHP_WIN32
	q = p + request->vpath_len;
	do {
		if (*q == '/') {
			*q = '\\';
		}
	} while (q-- > p);
#endif
	p += request->vpath_len;
	*p = '\0';
	q = p;
	while (q > buf) {
		if (!php_sys_stat(buf, &sb)) {
			if (sb.st_mode & S_IFDIR) {
				const char **file = index_files;
				if (q[-1] != DEFAULT_SLASH) {
					*q++ = DEFAULT_SLASH;
				}
				while (*file) {
					size_t l = strlen(*file);
					memmove(q, *file, l + 1);
					if (!php_sys_stat(buf, &sb) && (sb.st_mode & S_IFREG)) {
						q += l;
						break;
					}
					file++;
				}
				if (!*file || is_static_file) {
					if (prev_path) {
						pefree(prev_path, 1);
					}
					pefree(buf, 1);
					return;
				}
			}
			break; /* regular file */
		}
		if (prev_path) {
			pefree(prev_path, 1);
			*q = DEFAULT_SLASH;
		}
		while (q > buf && *(--q) != DEFAULT_SLASH);
		prev_path_len = p - q;
		prev_path = pestrndup(q, prev_path_len, 1);
		*q = '\0';
	}
	if (prev_path) {
		request->path_info_len = prev_path_len;
#ifdef PHP_WIN32
		while (prev_path_len--) {
			if (prev_path[prev_path_len] == '\\') {
				prev_path[prev_path_len] = '/';
			}
		}
#endif
		request->path_info = prev_path;
		pefree(request->vpath, 1);
		request->vpath = pestrndup(vpath, q - vpath, 1);
		request->vpath_len = q - vpath;
		request->path_translated = buf;
		request->path_translated_len = q - buf;
	} else {
		pefree(request->vpath, 1);
		request->vpath = pestrndup(vpath, q - vpath, 1);
		request->vpath_len = q - vpath;
		request->path_translated = buf;
		request->path_translated_len = q - buf;
	}
#ifdef PHP_WIN32
	{
		uint32_t i = 0;
		for (;i<request->vpath_len;i++) {
			if (request->vpath[i] == '\\') {
				request->vpath[i] = '/';
			}
		}
	}
#endif
	request->sb = sb;
}