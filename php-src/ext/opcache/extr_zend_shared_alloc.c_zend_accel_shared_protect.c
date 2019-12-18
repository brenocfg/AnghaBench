void zend_accel_shared_protect(int mode)
{
#ifdef HAVE_MPROTECT
	int i;

	if (!smm_shared_globals) {
		return;
	}

	if (mode) {
		mode = PROT_READ;
	} else {
		mode = PROT_READ|PROT_WRITE;
	}

	for (i = 0; i < ZSMMG(shared_segments_count); i++) {
		mprotect(ZSMMG(shared_segments)[i]->p, ZSMMG(shared_segments)[i]->end, mode);
	}
#elif defined(ZEND_WIN32)
	int i;

	if (!smm_shared_globals) {
		return;
	}

	if (mode) {
		mode = PAGE_READONLY;
	} else {
		mode = PAGE_READWRITE;
	}

	for (i = 0; i < ZSMMG(shared_segments_count); i++) {
		DWORD oldProtect;
		if (!VirtualProtect(ZSMMG(shared_segments)[i]->p, ZSMMG(shared_segments)[i]->end, mode, &oldProtect)) {
			zend_accel_error(ACCEL_LOG_ERROR, "Failed to protect memory");
		}
	}
#endif
}